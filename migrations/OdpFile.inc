<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpFile extends DrupalFile7Migration {
  public $current_row;

  public function __construct($arguments) {
    parent::__construct($arguments);
    //$this->destination->setFileClass('MigrateFileUri');

  }

  public function prepareRow($row){
    //parent::prepareRow($row);
    $this->destination->setFileClass('MigrateFileUriCustom');
    $this->current_row = $row;
  }
}

class MigrateFileUriCustom extends MigrateFileBase {
  public function processFile($value, $owner) {
    $migration = Migration::currentMigration();
    $new_file = clone $migration->current_row;
    unset($new_file->fid);
    $file = migrate_odp_file_save_custom($new_file);
    if (is_object($file)) {
      $this->markForPreservation($file->fid);
      return $file;
    }
    else {
      return FALSE;
    }
  }
}
