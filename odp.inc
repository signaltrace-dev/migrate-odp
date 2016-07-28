<?php

abstract class OdpMigration extends Migration{
  public function __construct($arguments){
    parent::__construct($arguments);
  }
}

class MigrateOdpDatasetRevision extends OdpMigration{
  public function __construct($arguments){
    parent::__construct($arguments);

    $query = Database::getConnection('default', 'odp')
      ->select('node_revision', 'r')
      ->fields('r');
    $query->join('node', 'n', 'r.nid = n.nid');
    $query->condition('n.type', 'dataset');
    $this->source = new MigrateSourceSQL($query, array(), NULL,
      array('map_joinable' => FALSE));

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'vid' => array('type' => 'int',
        'unsigned' => TRUE,
         'not null' => TRUE,
         'description' => 'Source VID',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNodeRevision('dataset');

    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('uid', 'uid');


    $this->addFieldMapping('field_abstract', 'field_abstract');
    $this->addFieldMapping('field_availability_state', 'field_availability_state')->defaultValue(1);
    $this->addFieldMapping('field_coordinate_list', 'field_coordinate_list');
    $this->addFieldMapping('field_coordinate_list_descriptio', 'field_coordinate_list_descriptio');
    $this->addFieldMapping('field_data_state', 'field_data_state')->defaultValue(1);
    $this->addFieldMapping('field_data_transfer_format', 'field_data_transfer_format');
    $this->addFieldMapping('field_data_transfer_format:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_data_type', 'field_data_type');
    $this->addFieldMapping('field_data_type:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_dataset_contact_person', 'field_dataset_contact_person');
    $this->addFieldMapping('field_dataset_contact_person_rol', 'field_dataset_contact_person_rol');
    $this->addFieldMapping('field_dataset_contact_person_rol:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_dataset_purpose', 'field_dataset_purpose');
    $this->addFieldMapping('field_dataset_source', 'field_dataset_source');
    $this->addFieldMapping('field_dataset_stakeholders', 'field_dataset_stakeholders');
    $this->addFieldMapping('field_date_range', 'field_date_range');
    $this->addFieldMapping('field_doi', 'field_doi');
    $this->addFieldMapping('field_ds_file_size', 'field_ds_file_size');
    $this->addFieldMapping('field_email_contact_on_update', 'field_email_contact_on_update');
    $this->addFieldMapping('field_error_analysis', 'field_error_analysis');
    $this->addFieldMapping('field_existing_file_on_server', 'field_existing_file_on_server');
    $this->addFieldMapping('field_external_data_source_url_', 'field_external_data_source_url_');
    $this->addFieldMapping('field_file_on_server', 'field_file_on_server');
    $this->addFieldMapping('field_file_upload', 'field_file_upload');
    $this->addFieldMapping('field_identify_state', 'field_identify_state')->defaultValue(1);
    $this->addFieldMapping('field_instruments', 'field_instruments');
    $this->addFieldMapping('field_metadata_contact_person', 'field_metadata_contact_person');
    $this->addFieldMapping('field_metadata_contact_person_ro', 'field_metadata_contact_person_ro');
    $this->addFieldMapping('field_metadata_contact_person_ro:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_metadata_state', 'field_metadata_state')->defaultValue(1);
    $this->addFieldMapping('field_methods', 'field_methods');
    $this->addFieldMapping('field_place_keywords', 'field_place_keywords');
    $this->addFieldMapping('field_place_keywords:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_provenance', 'field_provenance');
    $this->addFieldMapping('field_public_availability', 'field_public_availability');
    $this->addFieldMapping('field_record_type', 'field_record_type');
    $this->addFieldMapping('field_record_type:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_repo_udi', 'field_griidc_udi');
    $this->addFieldMapping('field_repository_state', 'field_repository_state')->defaultValue(1);
    $this->addFieldMapping('field_research_expedition', 'field_blog_title');
    $this->addFieldMapping('field_research_expedition:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_research_location', 'field_research_location');
    $this->addFieldMapping('field_research_location:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_sampling_scales_and_rates', 'field_sampling_scales_and_rates');
    $this->addFieldMapping('field_spatial_non_spatial_select', 'field_spatial_non_spatial_select');
    $this->addFieldMapping('field_supplemental_information_d', 'field_supplemental_information_d');
    $this->addFieldMapping('field_task', 'field_task');
    $this->addFieldMapping('field_task:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_theme_keywords', 'field_theme_keywords');
    $this->addFieldMapping('field_theme_keywords:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_time_period_desc_text', 'field_time_period_desc_text');
    $this->addFieldMapping('field_time_period_description_li', 'field_time_period_description_li');
    $this->addFieldMapping('field_topic_category_keywords', 'field_topic_category_keywords');
    $this->addFieldMapping('field_topic_category_keywords:source_type')->defaultValue('tid');

    $this->addFieldMapping('field_use_this_dataset_as_a_temp', 'field_use_this_dataset_as_a_temp');
  }
}
