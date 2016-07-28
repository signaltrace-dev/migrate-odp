<?php

/**
 * A migration that is reused for each source CSV file.
 */
class OdpMigration extends Migration {
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

  public function saveMessage($message, $level = MigrationBase::MESSAGE_ERROR) {
    switch ($level) {
      case MigrationBase::MESSAGE_ERROR:
      case MigrationBase::MESSAGE_WARNING:
        parent::saveMessage($message, $level);
        break;
      case MigrationBase::MESSAGE_NOTICE:
        Migration::displayMessage($message);
        break;
      default:
        // Ignore INFORMATIONAL messages unless verbose mode is
        // enabled.
        if (function_exists('drush_get_context') && drush_get_context(DRUSH_VERBOSE)) {
          Migration::displayMessage($message);
        }
        break;
    }
  }
}
