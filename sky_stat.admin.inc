<?php

/**
 * @file
 * Admin page callbacks for the sky_stat module.
 */


/**
 * Form constructor for the sky_stat administration form.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function sky_stat_settings_form() {
  // Content counter settings.
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content viewing counter settings'),
  );
  $form['content']['sky_stat_count_content_views'] = array(
    '#type' => 'checkbox',
    '#title' => t('Count content views'),
    '#default_value' => variable_get('sky_stat_count_content_views', 0),
    '#description' => t('Increment a counter each time content is viewed.'),
  );
  $form['content']['sky_stat_count_content_views_ajax'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Ajax to increment the counter'),
    '#default_value' => variable_get('sky_stat_count_content_views_ajax', 0),
    '#description' => t('Perform the count asynchronously after page load rather than during page generation.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="sky_stat_count_content_views"]' => array('checked' => FALSE),
      ),
    ),
  );

    $roles         = user_roles();
    $default_roles = variable_get('sky_stat_roles', array());

    $form['filter'] = array(
      '#type'  => 'fieldset',
      '#title' => t('Filter Settings'),
    );

    $form['filter']['sky_stat_noadmin'] = array(
      '#type'          => 'checkbox',
      '#title'         => t('Ignore administrator (User-1)'),
      '#description'   => t("Ignore the special administrator account's accesses to this site."),
      '#default_value' => variable_get('sky_stat_noadmin', FALSE),
    );

    $form['filter']['sky_stat_roles'] = array(
      '#type'          => 'checkboxes',
      '#title'         => t('Roles to ignore'),
      '#description'   => t('Ignore accesses by users in any of the checked roles.'),
      '#default_value' => $default_roles,
      '#options'       => $roles,
    );

    if (module_exists('browscap')) {
      $form['filter']['sky_stat_crawlers'] = array(
        '#type'          => 'checkbox',
        '#title'         => t('Ignore crawlers'),
        '#description'   => t("Ignore search engine crawlers' accesses to this site."),
        '#default_value' => variable_get('sky_stat_crawlers', FALSE),
      );
    }

  $form['#validate'][] = 'sky_stat_form_statistics_settings_validate';

  return system_settings_form($form);
}

function sky_stat_form_statistics_settings_validate(&$form, &$form_state) {
  $values = &$form_state['values'];
  $values['sky_stat_roles'] = array_filter($values['sky_stat_roles']);
}