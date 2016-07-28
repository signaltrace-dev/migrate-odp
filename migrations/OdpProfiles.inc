<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpProfile extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    module_load_include('inc', 'research_pipe', 'research_pipe.rules');

    $this->addFieldMapping('field_first_name', 'field_first_name');
    $this->addFieldMapping('field_middle_name', 'field_middle_name');
    $this->addFieldMapping('field_last_name', 'field_last_name');

    $this->addFieldMapping('field_photo', 'field_photo')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_photo:file_class')
     ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_photo:preserve_files')
      ->defaultValue(TRUE);

    $this->addFieldMapping('field_contact_position', 'field_contact_position');

    $this->addFieldMapping('field_institutional_department', 'field_institutional_department')
      ->sourceMigration('TaxonomyTerms_institutional_departments');
    $this->addFieldMapping('field_institutional_department:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_phone', 'field_phone');
    $this->addFieldMapping('field_profile_address', 'field_profile_address');
    $this->addFieldMapping('field_email', 'field_email');
    $this->addFieldMapping('field_website_url', 'field_website_url');
    $this->addFieldMapping('field_alternate_email_addresses', 'field_alternate_email_addresses');
  }
}
