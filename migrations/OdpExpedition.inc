<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpExpedition extends DrupalTerm7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_cruise_participants', 'field_cruise_participants')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_research_vessel', 'field_research_vessel');
    $this->addFieldMapping('field_cruise_identification_name', 'field_cruise_identification_name');
    $this->addFieldMapping('field_dates_of_expedition', 'field_date_range');

    $this->addFieldMapping('field_expedition_location', 'field_expedition_location')
      ->sourceMigration('TaxonomyTerms_location');
    $this->addFieldMapping('field_expedition_location:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_chief_scientist', 'field_chief_scientist')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_objectives', 'field_objectives');

    $this->addFieldMapping('field_cruise_report', 'field_cruise_report')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_cruise_report:file_class')
     ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_cruise_report:preserve_files')
     ->defaultValue(TRUE);

    $this->addFieldMapping('field_photo', 'field_photo')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_photo:preserve_files')
      ->defaultValue(TRUE);
    $this->addFieldMapping('field_photo:file_class')
     ->defaultValue('MigrateFileFid');
  }

  public function prepareRow($row){
    parent::prepareRow($row);

    $row->field_date_range = drupal_json_encode(
    array(
      'from' => (string) $row->field_dates_of_expedition[0],
      'to' => (string) $row->{'field_dates_of_expedition:value2'}[0],
   ));
  }
}
