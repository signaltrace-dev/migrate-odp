<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpUser extends DrupalUser7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->newOnly = TRUE;

    $this->addFieldMapping('field_first_name', 'field_first_name');
    $this->addFieldMapping('field_last_name', 'field_last_name');

    //$this->addFieldMapping('field_my_author_profile', 'field_my_author_profile');

  }

  public function preImport(){
    parent::preImport();
    variable_set('comment_maintain_node_statistics', FALSE);
  }

  public function postImport(){
    parent::postImport();
    variable_set('comment_maintain_node_statistics', TRUE);
    devel_rebuild_node_comment_statistics();
  }
}
