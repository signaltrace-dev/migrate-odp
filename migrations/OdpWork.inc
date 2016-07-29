<?php

class OdpWork extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_my_author_profile', 'field_participant_name')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_work_role_term', 'participant_role_tid')
      ->sourceMigration('TaxonomyTerms_participant_roles');
    $this->addFieldMapping('field_work_role_term:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_institutional_department', 'field_institutional_department')
      ->sourceMigration('TaxonomyTerms_institutional_departments');
    $this->addFieldMapping('field_institutional_department:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_date_range_month_year', 'date_range'); // prepareRow

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('User');
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    $row->participant_role_tid = !empty($row->{'field_participant_role:tid'}[0]) ? $row->{'field_participant_role:tid'}[0] : NULL;
    $start_date = !empty($row->{'field_participant_role:date_from_timestamp'}[0]) ? $row->{'field_participant_role:date_from_timestamp'}[0] : NULL;
    $end_date = !empty($row->{'field_participant_role:date_to_timestamp'}[0]) ? $row->{'field_participant_role:date_to_timestamp'}[0] : NULL;

    $row->date_range = drupal_json_encode(
    array(
      'from' => (string) $start_date,
      'to' => (string) $end_date,
   ));
  }

  public function complete($entity, stdClass $row){
    $wrapper = entity_metadata_wrapper('node', $entity);
    $type = isset($wrapper->field_work_role_term) ? $wrapper->field_work_role_term->value() : NULL;
    $dept = isset($wrapper->field_institutional_department) ? $wrapper->field_institutional_department->value() : NULL;
    $date_range = isset($wrapper->field_date_range_month_year) ? $wrapper->field_date_range_month_year->value() : NULL;
    $date_from = !empty($date_range['value']) ? $date_range['value'] : NULL;
    $date_to = !empty($date_range['value2']) ? $date_range['value2'] : NULL;

    if(!empty($type) && !empty($dept)){
      $entity->title = migrate_odp_build_experience_title($type->tid, $dept->tid, $date_from, $date_to);
      $wrapper->save();
    }


    $author_profile = $wrapper->field_my_author_profile->value();
    if(!empty($author_profile)){
      $work = !empty($author_profile->field_affiliations_work[LANGUAGE_NONE]) ? $author_profile->field_affiliations_work[LANGUAGE_NONE] : array();
      $work[] = array('target_id' => $entity->nid);
      $author_profile->field_affiliations_work[LANGUAGE_NONE] = $work;
      node_save($author_profile);
    }

  }
}
