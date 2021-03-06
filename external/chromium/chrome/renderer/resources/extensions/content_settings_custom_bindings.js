// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Custom bindings for the contentSettings API.

var chromeHidden = requireNative('chrome_hidden').GetChromeHidden();
var sendRequest = require('sendRequest').sendRequest;
var validate = require('schemaUtils').validate;

chromeHidden.registerCustomType('contentSettings.ContentSetting', function() {
  function extendSchema(schema) {
    var extendedSchema = schema.slice();
    extendedSchema.unshift({'type': 'string'});
    return extendedSchema;
  }

  function ContentSetting(contentType, settingSchema) {
    this.get = function(details, callback) {
      var getSchema = this.functionSchemas.get.definition.parameters;
      validate([details, callback], getSchema);
      return sendRequest('contentSettings.get',
                         [contentType, details, callback],
                         extendSchema(getSchema));
    };
    this.set = function(details, callback) {
      var setSchema = this.functionSchemas.set.definition.parameters.slice();
      setSchema[0].properties.setting = settingSchema;
      validate([details, callback], setSchema);
      return sendRequest('contentSettings.set',
                         [contentType, details, callback],
                         extendSchema(setSchema));
    };
    this.clear = function(details, callback) {
      var clearSchema = this.functionSchemas.clear.definition.parameters;
      validate([details, callback], clearSchema);
      return sendRequest('contentSettings.clear',
                         [contentType, details, callback],
                         extendSchema(clearSchema));
    };
    this.getResourceIdentifiers = function(callback) {
      var schema =
          this.functionSchemas.getResourceIdentifiers.definition.parameters;
      validate([callback], schema);
      return sendRequest(
          'contentSettings.getResourceIdentifiers',
          [contentType, callback],
          extendSchema(schema));
    };
  }

  return ContentSetting;
});
