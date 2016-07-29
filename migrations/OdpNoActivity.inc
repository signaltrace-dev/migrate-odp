<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpNoActivity extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_quarter', 'field_quarter');
    $this->addFieldMapping('field_year', 'field_year');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('User');
  }

  public function prepareRow($row){
    parent::prepareRow($row);
  }
}
