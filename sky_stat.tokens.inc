<?php

/**
 * @file
 * Builds placeholder replacement tokens for node visitor sky_stat.
 */

/**
 * Implements hook_token_info().
 */
function sky_stat_token_info() {
  $node['total-count'] = array(
    'name' => t("Number of views"),
    'description' => t("The number of visitors who have read the node."),
  );
  $node['day-count'] = array(
    'name' => t("Views today"),
    'description' => t("The number of visitors who have read the node today."),
  );
  $node['last-view'] = array(
    'name' => t("Last view"),
    'description' => t("The date on which a visitor last read the node."),
    'type' => 'date',
  );

  return array(
    'tokens' => array('node' => $node),
  );
}

/**
 * Implements hook_tokens().
 */
function sky_stat_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);
  $replacements = array();

  if ($type == 'node' & !empty($data['node'])) {
    $node = $data['node'];

    foreach ($tokens as $name => $original) {
      if ($name == 'total-count') {
        $sky_stat = sky_stat_get($node->nid);
        $replacements[$original] = $sky_stat['totalcount'];
      }
      elseif ($name == 'day-count') {
        $sky_stat = sky_stat_get($node->nid);
        $replacements[$original] = $sky_stat['daycount'];
      }
      elseif ($name == 'last-view') {
        $sky_stat = sky_stat_get($node->nid);
        $replacements[$original] = format_date($sky_stat['timestamp']);
      }
    }

    if ($created_tokens = token_find_with_prefix($tokens, 'last-view')) {
      $sky_stat = sky_stat_get($node->nid);
      $replacements += token_generate('date', $created_tokens, array('date' => $sky_stat['timestamp']), $options);
    }
  }

  return $replacements;
}
