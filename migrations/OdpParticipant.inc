<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpParticipant extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_participant_name', 'field_participant_name')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_email', 'field_email');

    $this->addFieldMapping('field_institutional_department', 'field_institutional_department')
      ->sourceMigration('TaxonomyTerms_institutional_departments');
    $this->addFieldMapping('field_institutional_department:source_type')
      ->defaultvalue('tid');
  }

  public function prepareRow($row){
    parent::prepareRow($row);
  }
}
