

self.addEventListener('install', function(event) {
	console.log('Service Worker: Install');
	console.log(event);
});


self.addEventListener('activate', function(event) {
	console.log('Service Worker: Activate');
	console.log(event);
});


self.addEventListener('fetch', function(event) {
	console.log('Service Worker: fetch - ' + event.request);
	console.log(event);
	event.respondWith(fetch(event.request)); // output the default stuff.
});


