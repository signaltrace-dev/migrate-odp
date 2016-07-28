<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpStudent extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_student_profile', 'field_student_profile')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_institutional_department', 'field_institutional_department')
      ->sourceMigration('TaxonomyTerms_institutional_departments');
    $this->addFieldMapping('field_institutional_department:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_supervisor_s_', 'field_supervisor_s_')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_tesis_or_research_topic', 'field_tesis_or_research_topic');
    $this->addFieldMapping('field_expected_yr_of_completion', 'field_expected_yr_of_completion');
    $this->addFieldMapping('field_link_to_dissertation_or_th', 'field_link_to_dissertation_or_th');
    $this->addFieldMapping('field_notes', 'field_notes');
  }

  public function prepareRow($row){
    parent::prepareRow($row);
  }
}
