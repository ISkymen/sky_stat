<?php

/**
 * @file
 * Handles counts of node views via Ajax with minimal bootstrap.
 */

/**
* Root directory of Drupal installation.
*/
define('DRUPAL_ROOT', substr($_SERVER['SCRIPT_FILENAME'], 0, strpos($_SERVER['SCRIPT_FILENAME'], '/sites/all/modules/custom/sky_stat/sky_stat.php')));
// Change the directory to the Drupal root.
chdir(DRUPAL_ROOT);

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_VARIABLES);
if (variable_get('sky_stat_count_content_views', 0) && variable_get('sky_stat_count_content_views_ajax', 0)) {
  if (isset($_POST['nid'])) {
    $nid = $_POST['nid'];
    if (is_numeric($nid)) {
      db_merge('sky_stat')
        ->key(array('nid' => $nid))
        ->fields(array(
          'totalcount' => 1,
          'yearcount' => 1,
          'monthcount' => 1,
          'weekcount' => 1,
          'daycount' => 1,
          'timestamp' => REQUEST_TIME,
        ))
        ->expression('totalcount', 'totalcount + 1')
        ->expression('yearcount', 'yearcount + 1')
        ->expression('monthcount', 'monthcount + 1')
        ->expression('weekcount', 'weekcount + 1')
        ->expression('daycount', 'daycount + 1')
        ->execute();
    }
  }
}
