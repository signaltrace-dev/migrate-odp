<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpWorkshop extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_date_range', 'field_date_range');
    $this->addFieldMapping('field_location_city', 'country');
    $this->addFieldMapping('field_location_city:administrative_area', 'state');
    $this->addFieldMapping('field_location_city:locality', 'city');

    $this->addFieldMapping('field_internal_external', 'field_internal_external');

    $this->addFieldMapping('field_organizer_s_', 'field_organizer_s_')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_participant_name', 'field_participant_name')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_number_of_participants', 'field_number_of_participants');
    $this->addFieldMapping('field_meeting_website', 'field_meeting_website');
    $this->addFieldMapping('field_repo_contribution_number', 'field_ecogig_contribution_number');
  }

  public function prepareRow($row){
    parent::prepareRow($row);
    $row->field_date_range = drupal_json_encode(
    array(
      'from' => (string) $row->field_date_range[0],
      'to' => (string) $row->{'field_date_range:value2'}[0],
   ));

   $row->country = $row->field_location_city[0];
   $row->state = $row->{'field_location_city:administrative_area'}[0];
   $row->city = $row->{'field_location_city:locality'}[0];
  }
}
