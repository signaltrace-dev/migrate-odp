<?php

/**
 * A migration that is reused for each source CSV file.
 */
class WorkshopMigration extends OdpMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'csvrownum' => array('type' => 'int',
                           'unsigned' => TRUE,
                           'not null' => TRUE,
                           'description' => 'Row ID',
                          ),
        ),
        MigrateDestinationNode::getKeySchema()
      );


    $columns = array(
      0 => array('field_internal_external', 'Internal / External'),
      1 => array('field_dates', 'Dates'),
      2 => array('field_location_city', 'Location'),
      3 => array('field_organizers', 'Organizers'),
      4 => array('body', 'Objectives'),
      5 => array('field_participant_name', 'Participants'),
      6 => array('field_meeting_website', 'Website URL')
    );

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceCSV($arguments['source_file'], $columns, array(
      'delimiter' => '^',
    ));


    $this->destination = new MigrateDestinationNode('workshop');

    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_internal_external', 'field_internal_external');
    $this->addFieldMapping('field_location_city', 'location_country');
    $this->addFieldMapping('field_location_city:administrative_area', 'location_state');
    $this->addFieldMapping('field_location_city:locality', 'location_city');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_date_range', 'date_range');
    $this->addFieldMapping('field_organizer_s_', 'field_organizers');
    $this->addFieldMapping('field_participant_name', 'field_participants');
    $this->addFieldMapping('field_meeting_website', 'field_meeting_website');
    $this->addFieldMapping('field_number_of_participants', 'field_number_of_participants');
  }

  /**
   * Construct the machine name from the source file name.
   */
  protected function generateMachineName($class_name = NULL) {
    return drupal_strtolower(pathinfo($this->arguments['source_file'],
                                      PATHINFO_FILENAME));
  }

  public function prepareRow($row) {
    $row->title = migrate_rp_handle_title_field($row->body);

    // Organizers - map to profiles if applicable
    $organizers = $row->field_organizers;
    $organizers_arr = explode(',', $organizers);

    $field_organizers = array();
    foreach($organizers_arr as $org){
      $profile_id = migrate_rp_handle_profile_field($org);
      if(!empty($profile_id)){
        $field_organizers[] = $profile_id;
      }
    }
    $row->field_organizers = $field_organizers;

    // Internal / External
    $str_int_ext = strtolower($row->field_internal_external);
    $int_ext = 0;
    switch($str_int_ext){
      case 'external':
        $int_ext = 1;
      break;
    }
    $row->field_internal_external = $int_ext;

    // Location - City, State, Country
    $location = $row->field_location_city;
    $location_arr = migrate_rp_handle_location_field($location);

    $row->location_country = $location_arr['country'];
    $row->location_state = $location_arr['state'];
    $row->location_city = $location_arr['city'];

    // Sometimes we have particpant names, other times we have a number. Fun!
    $participants = $row->field_participant_name;
    $participant_count = 0;
    $matches = array();
    if (preg_match("/\d+/", $participants, $matches) != FALSE){
      $participant_count = isset($matches[0]) ? $matches[0] : 0;
    }
    else{
      $participant_arr = explode(',', $participants);

      $participant_count = count($participant_arr);
      $field_participants = array();
      foreach($participant_arr as $part){
        $profile_id = migrate_rp_handle_profile_field(trim($part));
        if(!empty($profile_id)){
          $field_participants[] = $profile_id;
        }
      }
      $row->field_participants = $field_participants;
    }
    $row->field_number_of_participants = $participant_count;

    $row->date_range = migrate_rp_parse_dates($row->field_dates);
  }
}
