// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// A guest that logs console messages.
// Note that the embedder has to initiate a postMessage first so that
// the guest has a reference to the embedder's window.
window.console.log('Guest script loading.');

// The window reference of the embedder to send post message reply.
var embedderWindowChannel = null;

var notifyEmbedder = function(msg_array) {
  embedderWindowChannel.postMessage(JSON.stringify(msg_array), '*');
};

var onPostMessageReceived = function(e) {
  embedderWindowChannel = e.source;
  var data = JSON.parse(e.data);
  if (data[0] == 'create-channel') {
    window.console.log('aaa. guest: create-channel');
    notifyEmbedder(['channel-created']);
    return;
  }

  // Tests.
  // These logs trigger event listeners in the embedder.
  switch (data[0]) {
    case 'test-1':
      window.console.log('log-one');  // LevelLog = 0.
      break;
    case 'test-2':
      window.console.warn('log-two');  // LevelWarning = 1.
      break;
    case 'test-3':
      window.console.error('log-three');  // LevelDebug = 2.
      break;
    case 'test-4':
      window.console.debug('log-four');  // LevelError = -1.
      break;
    case 'test-throw':
      throw Error('log-five');
      break;
  }
};

window.addEventListener('message', onPostMessageReceived, false);
