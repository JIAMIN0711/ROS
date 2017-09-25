
"use strict";

let AddTwoInts = require('./AddTwoInts.js')
let TestNestedService = require('./TestNestedService.js')
let SendBytes = require('./SendBytes.js')
let TestEmpty = require('./TestEmpty.js')
let TestMultipleRequestFields = require('./TestMultipleRequestFields.js')
let TestArrayRequest = require('./TestArrayRequest.js')
let TestRequestAndResponse = require('./TestRequestAndResponse.js')
let TestMultipleResponseFields = require('./TestMultipleResponseFields.js')
let TestRequestOnly = require('./TestRequestOnly.js')
let TestResponseOnly = require('./TestResponseOnly.js')

module.exports = {
  AddTwoInts: AddTwoInts,
  TestNestedService: TestNestedService,
  SendBytes: SendBytes,
  TestEmpty: TestEmpty,
  TestMultipleRequestFields: TestMultipleRequestFields,
  TestArrayRequest: TestArrayRequest,
  TestRequestAndResponse: TestRequestAndResponse,
  TestMultipleResponseFields: TestMultipleResponseFields,
  TestRequestOnly: TestRequestOnly,
  TestResponseOnly: TestResponseOnly,
};
