

if ('serviceWorker' in navigator) {
  navigator.serviceWorker.register('/js/service-worker.js').then(function(reg) {

    if(reg.installing) {
      console.log('Service worker installing');
    } else if(reg.waiting) {
      console.log('Service worker installed');
    } else if(reg.active) {
      console.log('Service worker active');
    }

  }).catch(function(error) {
    // registration failed
    console.log('Registration failed with ' + error);
  });
};


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


