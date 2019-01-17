
(function() {
  'use strict';

  var app = {
    isLoading: true,
    spinner: document.querySelector('.spinner'),
  };



  app.doStuff = function(data) {
    alert('were doing stuff:' + data);
    if (app.isLoading) {
    //  app.spinner.setAttribute('hidden', true);
    
      //app.isLoading = false;
    }
  };

  app.doStuff('Start it');
})();
