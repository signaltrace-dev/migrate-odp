<?php

/**
 * Implements hook_flush_caches().
 */
function migrate_d2d_flush_caches() {
   migrate_d2d_register_migrations();
}

/**
 * Register all D7->D7 migrations.
 */
function migrate_d2d_register_migrations() {
  $common_arguments = array(
    'source_connection' => 'odp',
    'source_version' => 7,
    'group_name' => 'odp',
  );

  $arguments = $common_arguments + array(
    'description' => t('Migration of roles from old site to new site'),
    'machine_name' => 'Role',
    'role_mappings' => array(
      'Administration' => 'Administration',
      'Data Manager' => 'Data Manager',
      'Guest Blogger' => 'Guest Blogger',
      'Information Technology' => 'Information Technology',
      'Principal Investigator (PI)' => 'Principal Investigator (PI)',
      'Program Director' => 'Program Director',
      'Public Outreach' => 'Public Outreach',
      'Research Professional' => 'Research Professional',
      'Chief Scientist' => 'Chief Scientist',
    ),
  );

  Migration::registerMigration('DrupalRole7Migration', $arguments['machine_name'], $arguments);

  $arguments = $common_arguments + array(
    'description' => t('Migration of users from old site to new site'),
    'machine_name' => 'User',
    'role_migration' => 'Role',
    'class_name' => 'OdpUser',
    'dependencies' => array(
      'Role',
    ),
  );

  Migration::registerMigration('OdpUser', $arguments['machine_name'], $arguments);

   // File migration
  $arguments = $common_arguments + array(
     'description' => t('Migrate all files'),
     'machine_name' => 'Files',
     'source_dir' => 'http://ecogig.local/sites/default/files',
     'destination_dir' => '',
  );

  Migration::registerMigration('DrupalFile7Migration', $arguments['machine_name'], $arguments);

   // Profile migration
  $arguments = $common_arguments + array(
     'description' => t('Migrate Profiles'),
     'machine_name' => 'Profile',
     'destination_type' => 'profile',
     'source_type' => 'profile',
     'dependencies' => array(
       'TaxonomyTerms_institutional_departments',
       'User',
     ),
  );

  Migration::registerMigration('OdpProfile', $arguments['machine_name'], $arguments);

  $vocabs = array(
    'contact_person_roles' => 'contact_person_roles',
    'data_type' => 'data_type',
    'dataset_file_formats' => 'dataset_file_formats',
    'dataset_place_keywords' => 'dataset_place_keywords',
    'dataset_record_types' => 'dataset_record_types',
    'institutional_departments' => 'institutional_departments',
    'dataset_theme_keywords' => 'dataset_theme_keywords',
    'dataset_topic_category_keywords' => 'dataset_topic_category_keywords',
    'task_title' => 'task_title',
    'gomri_theme' => 'repo_theme',
    'journal' => 'journal',
    'location' => 'location',
  );

  foreach($vocabs as $source_vocab => $dest_vocab){
    $arguments = $common_arguments + array(
       'description' => t('Migrate ' . $source_vocab),
       'machine_name' => 'TaxonomyTerms_' . $dest_vocab,
       'source_vocabulary' => $source_vocab,
       'destination_vocabulary' => $dest_vocab,
    );

    Migration::registerMigration('DrupalTerm7Migration', $arguments['machine_name'], $arguments);
  }

  $arguments = $common_arguments + array(
    'description' => t('Migrate Expeditions'),
    'machine_name' => t('Expeditions'),
    'source_vocabulary' => 'blog_title',
    'destination_vocabulary' => 'expedition',
    'class_name' => 'OdpExpedition',
    'dependencies' => array(
      'TaxonomyTerms_location',
      'Profile',
      'Files',
    ),
  );
  Migration::registerMigration('OdpExpedition', $arguments['machine_name'], $arguments);

  $arguments = $common_arguments + array(
    'description' => t('Migrate Presentations'),
    'machine_name' => t('Presentations'),
    'destination_type' => 'presentation',
    'source_type' => 'presentation',
    'class_name' => 'OdpPresentation',
    'dependencies' => array(
      'TaxonomyTerms_repo_theme',
      'Profile'
    ),
  );
  Migration::registerMigration('OdpPresentation', $arguments['machine_name'], $arguments);
}

function migrate_odp_migrate_api(){
  $common_arguments = array(
    'source_connection' => 'odp',
    'source_version' => 7,
    'group_name' => 'odp',
  );

  $api = array(
    'api' => 2,
    'groups' => array(
      'odp' => array(
        'title' => t('ODP Migrations'),
      ),
    ),

    'migrations' => array(

    ),
  );

  return $api;
}
