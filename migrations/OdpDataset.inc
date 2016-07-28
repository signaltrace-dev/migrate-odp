<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpDataset extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_record_type', 'field_record_type')
      ->sourceMigration('TaxonomyTerms_dataset_record_types');
    $this->addFieldMapping('field_record_type:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_use_this_dataset_as_a_temp', 'field_use_this_dataset_as_a_temp');

    $this->addFieldMapping('field_task', 'field_task')
      ->sourceMigration('TaxonomyTerms_task_title');
    $this->addFieldMapping('field_task:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_dataset_contact_person', 'field_dataset_contact_person')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_dataset_contact_person_rol', 'field_dataset_contact_person_rol')
      ->sourceMigration('TaxonomyTerms_contact_person_roles');
    $this->addFieldMapping('field_dataset_contact_person_rol:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_dataset_stakeholders', 'field_dataset_stakeholders')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_research_expedition', 'field_research_expedition')
      ->sourceMigration('Expeditions');
    $this->addFieldMapping('field_research_expedition:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_data_type', 'field_data_type')
      ->sourceMigration('TaxonomyTerms_data_type');
    $this->addFieldMapping('field_data_type:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_abstract', 'field_abstract');
    $this->addFieldMapping('field_dataset_purpose', 'field_dataset_purpose');
    $this->addFieldMapping('field_supplemental_information_d', 'field_supplemental_information_d');
    $this->addFieldMapping('field_methods', 'field_use_this_datasetfield_methods_as_a_temp');
    $this->addFieldMapping('field_instruments', 'field_instruments');
    $this->addFieldMapping('field_sampling_scales_and_rates', 'field_sampling_scales_and_rates');
    $this->addFieldMapping('field_error_analysis', 'field_error_analysis');
    $this->addFieldMapping('field_provenance', 'field_provenance');
    $this->addFieldMapping('field_repo_udi', 'field_griidc_udi');
    $this->addFieldMapping('field_doi', 'field_doi');


    $this->addFieldMapping('field_theme_keywords', 'field_theme_keywords')
      ->sourceMigration('TaxonomyTerms_dataset_theme_keywords');
    $this->addFieldMapping('field_theme_keywords:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_place_keywords', 'field_place_keywords')
      ->sourceMigration('TaxonomyTerms_dataset_place_keywords');
    $this->addFieldMapping('field_place_keywords:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_topic_category_keywords', 'field_topic_category_keywords')
      ->sourceMigration('TaxonomyTerms_dataset_topic_category_keywords');
    $this->addFieldMapping('field_topic_category_keywords:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_research_location', 'field_research_location')
      ->sourceMigration('TaxonomyTerms_location');
    $this->addFieldMapping('field_research_location:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_spatial_non_spatial_select', 'field_spatial_non_spatial_select');
    $this->addFieldMapping('field_coordinate_list', 'field_coordinate_list');
    $this->addFieldMapping('field_coordinate_list_descriptio', 'field_coordinate_list_descriptio');

    $this->addFieldMapping('field_metadata_contact_person', 'field_metadata_contact_person')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_metadata_contact_person_ro', 'field_metadata_contact_person_ro')
      ->sourceMigration('TaxonomyTerms_contact_person_roles');
    $this->addFieldMapping('field_metadata_contact_person_ro:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_dataset_source', 'field_dataset_source');

    $this->addFieldMapping('field_file_upload', 'field_file_upload')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_file_upload:file_class')
     ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_file_upload:preserve_files')
     ->defaultValue(TRUE);

    $this->addFieldMapping('field_external_data_source_url_', 'field_external_data_source_url_');

    $this->addFieldMapping('field_existing_file_on_server', 'field_existing_file_on_server')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_existing_file_on_server:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_existing_file_on_server:preserve_files')
      ->defaultValue(TRUE);

    $this->addFieldMapping('field_file_on_server', 'field_file_on_server');

    $this->addFieldMapping('field_data_transfer_format', 'field_data_transfer_format')
      ->sourceMigration('TaxonomyTerms_dataset_file_formats');
    $this->addFieldMapping('field_data_transfer_format:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_ds_file_size', 'field_ds_file_size');
    $this->addFieldMapping('field_public_availability', 'field_public_availability');
    $this->addFieldMapping('field_identify_state', 'field_identify_state');
    $this->addFieldMapping('field_metadata_state', 'field_metadata_state');
    $this->addFieldMapping('field_data_state', 'field_data_state');
    $this->addFieldMapping('field_repository_state', 'field_repository_state');
    $this->addFieldMapping('field_availability_state', 'field_availability_state');
    $this->addFieldMapping('field_email_contact_on_update', 'field_email_contact_on_update');
    $this->addFieldMapping('field_time_period_description_li', 'field_time_period_description_li');
    $this->addFieldMapping('field_date_range', 'field_date_range');
    $this->addFieldMapping('field_time_period_desc_text', 'field_time_period_desc_text');
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
