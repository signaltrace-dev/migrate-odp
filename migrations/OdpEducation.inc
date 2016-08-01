<?php

class OdpEducation extends DrupalNode7Migration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_my_author_profile', 'field_student_profile')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_student_type_term', 'student_type_tid')
      ->sourceMigration('TaxonomyTerms_student_types');
    $this->addFieldMapping('field_student_type_term:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_institutional_department', 'field_institutional_department')
      ->sourceMigration('TaxonomyTerms_institutional_departments');
    $this->addFieldMapping('field_institutional_department:source_type')
      ->defaultvalue('tid');

    $this->addFieldMapping('field_date_range_month_year', 'date_range'); // prepareRow

    $this->addFieldMapping('field_supervisor_s_', 'field_supervisor_s_')
      ->sourceMigration('Profile');

    $this->addFieldMapping('field_tesis_or_research_topic', 'field_tesis_or_research_topic');
    $this->addFieldMapping('field_expected_yr_of_completion', 'field_expected_yr_of_completion');
    $this->addFieldMapping('field_link_to_dissertation_or_th', 'field_link_to_dissertation_or_th');
    $this->addFieldMapping('field_notes', 'field_notes');
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('User');
  }

  public function prepareRow($row) {
    parent::prepareRow($row);

    $row->student_type_tid = !empty($row->{'field_student_type:tid'}[0]) ? $row->{'field_student_type:tid'}[0] : NULL;
    $start_date = !empty($row->{'field_student_type:date_from_timestamp'}[0]) ? $row->{'field_student_type:date_from_timestamp'}[0] : NULL;
    $end_date = !empty($row->{'field_student_type:date_to_timestamp'}[0]) ? $row->{'field_student_type:date_to_timestamp'}[0] : NULL;

    $row->date_range = drupal_json_encode(
    array(
      'from' => (string) $start_date,
      'to' => (string) $end_date,
   ));
  }

  public function complete($entity, stdClass $row){
    $wrapper = entity_metadata_wrapper('node', $entity);
    $student_type = isset($wrapper->field_student_type_term) ? $wrapper->field_student_type_term->value() : NULL;
    $dept = isset($wrapper->field_institutional_department) ? $wrapper->field_institutional_department->value() : NULL;
    $date_range = isset($wrapper->field_date_range_month_year) ? $wrapper->field_date_range_month_year->value() : NULL;
    $date_from = !empty($date_range['value']) ? $date_range['value'] : NULL;
    $date_to = !empty($date_range['value2']) ? $date_range['value2'] : NULL;

    if(!empty($student_type) && !empty($dept)){
      $entity->title = migrate_odp_build_experience_title($student_type->tid, $dept->tid, $date_from, $date_to);
      $wrapper->save();
    }


    $author_profile = $wrapper->field_my_author_profile->value();
    if(!empty($author_profile)){
      $education = !empty($author_profile->field_affiliations_school[LANGUAGE_NONE]) ? $author_profile->field_affiliations_school[LANGUAGE_NONE] : array();
      $education[] = array('target_id' => $entity->nid);
      $author_profile->field_affiliations_school[LANGUAGE_NONE] = $education;
      node_save($author_profile);
    }

  }
}
