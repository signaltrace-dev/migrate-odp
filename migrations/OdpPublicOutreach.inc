<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpPublicOutreach extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_outreach_type', 'field_outreach_type');
    $this->addFieldMapping('field_other', 'field_other');
    $this->addFieldMapping('field_date_range', 'field_date_range');

    $this->addFieldMapping('field_participant_name', 'field_participant_name')
      ->sourceMigration('Profile');
    $this->addFieldMapping('field_contrib_author', 'field_contrib_author')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_po_target_audience_s_', 'field_po_target_audience_s_');
    $this->addFieldMapping('field_po_number_impacted', 'field_po_number_impacted');
    $this->addFieldMapping('field_impacts_outcomes', 'field_impacts_outcomes');
    $this->addFieldMapping('field_repo_contribution_number', 'field_repo_contribution_number');
    $this->addFieldMapping('field_website_url', 'field_website_url');
    $this->addFieldMapping('field_notes', 'field_notes');

    $this->addFieldMapping('field_data_theme', 'field_gomri_theme')
      ->sourceMigration('TaxonomyTerms_repo_theme');
    $this->addFieldMapping('field_data_theme:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_po_partners_in_activity', 'field_po_partners_in_activity');

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
  }
}
