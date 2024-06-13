// Load page information from cache if available
// Register service worker
if ("serviceWorker" in navigator) {
    window.addEventListener("load", () => {
        navigator.serviceWorker.register("/static/js/serviceWorker.js").then(() => {
            console.log("ServiceWorker successfully registered!");
        }, (error) => {
            console.error("ServiceWorker registration failed!", error);
        });
    });
}

// Add a fetch event listener to the service worker
self.addEventListener("fetch", (event) => {
    event.respondWith(
        caches.match(event.request).then((response) => {
            // Cache hit - return response
            if (response) {
                return response;
            }
            // No cache hit - fetch response and add to cache
            return fetch(event.request).then((response) => {
                // Check if response is valid
                if (!response || response.status !== 200 || response.type !== "basic") {
                    return response;
                }
                // Clone response and add to cache
                var responseToCache = response.clone();
                caches.open("my-site-cache-v1").then((cache) => {
                    cache.put(event.request, responseToCache);
                });
                return response;
            });
        })
    );
});

