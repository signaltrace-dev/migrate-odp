<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpPresentation extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_date_range', 'field_date_range');
    $this->addFieldMapping('field_presentation_type', 'field_presentation_type');
    $this->addFieldMapping('field_conference_name', 'field_conference_name');
    $this->addFieldMapping('field_location_city', 'country');
    $this->addFieldMapping('field_location_city:administrative_area', 'state');
    $this->addFieldMapping('field_location_city:locality', 'city');

    $this->addFieldMapping('field_presenter_profile', 'field_presenter_profile')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_any_authors_student', 'field_any_authors_student');

    $this->addFieldMapping('field_contrib_author', 'field_contrib_author')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_student_authors', 'field_student_authors');
    $this->addFieldMapping('field_repo_contribution_number', 'field_repo_contribution_number');
    $this->addFieldMapping('field_link_single', 'field_link_single');

    $this->addFieldMapping('field_data_theme', 'field_gomri_theme')
      ->sourceMigration('TaxonomyTerms_repo_theme');
    $this->addFieldMapping('field_data_theme:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('User');
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
