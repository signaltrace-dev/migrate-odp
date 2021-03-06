<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpRole extends DrupalRole7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);
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

  public function prepareRow($row) {
    parent::prepareRow($row);
  }
}
