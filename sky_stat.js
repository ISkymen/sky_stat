(function ($) {
  $(document).ready(function() {
    $.ajax({
      type: "POST",
      cache: false,
      url: Drupal.settings.sky_stat.url,
      data: Drupal.settings.sky_stat.data
    });
  });
})(jQuery);
