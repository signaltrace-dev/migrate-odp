<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpPublication extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_contrib_author', 'field_contrib_author')
      ->sourceMigration('Profile');
    $this->addFieldMapping('field_any_authors_student', 'field_any_authors_student');
    $this->addFieldMapping('field_grant', 'field_grant');

    $this->addFieldMapping('field_journal_title', 'field_journal_title')
      ->sourceMigration('TaxonomyTerms_journal');
    $this->addFieldMapping('field_journal_title:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_journal_volume', 'field_journal_volume');
    $this->addFieldMapping('field_year', 'field_year');
    $this->addFieldMapping('field_journal_issue', 'field_journal_issue');

    $this->addFieldMapping('field_page_numbers:from', 'field_page_numbers_from');
    $this->addFieldMapping('field_page_numbers:to', 'field_page_numbers_to');


    $this->addFieldMapping('field_doi', 'field_doi');
    $this->addFieldMapping('field_citation', 'field_citation');

    $this->addFieldMapping('field_publications_workflow', 'field_publications_workflow');

    $this->addFieldMapping('field_submission_date', 'field_submission_date');
    $this->addFieldMapping('field_date_published', 'field_date_published');
    $this->addFieldMapping('field_repo_contribution_number', 'field_ecogig_contribution_number');

    $this->addFieldMapping('field_dataset', 'field_dataset')
      ->sourceMigration('Datasets');

    $this->addFieldMapping('field_link_to_publication_and_or', 'field_link_to_publication_and_or');
    $this->addFieldMapping('field_publication_notes', 'field_publication_notes');

    $this->addFieldMapping('field_data_theme', 'field_gomri_theme')
      ->sourceMigration('TaxonomyTerms_repo_theme');
    $this->addFieldMapping('field_data_theme:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_file_upload', 'field_file_upload')
      ->sourceMigration('Files');
    $this->addFieldMapping('field_file_upload:file_class')
     ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_file_upload:preserve_files')
     ->defaultValue(TRUE);

     $this->addFieldMapping('uid', 'uid')
       ->sourceMigration('User');
  }

  public function prepareRow($row){
    parent::prepareRow($row);
    $row->field_page_numbers_from = !empty($row->field_page_numbers[0]) ? $row->field_page_numbers[0] : NULL;
    $row->field_page_numbers_to = !empty($row->{'field_page_numbers:to'}[0]) ? $row->{'field_page_numbers:to'}[0] : NULL;
  }
}
