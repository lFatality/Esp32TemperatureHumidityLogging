/*
// logging spreadsheet: https://docs.google.com/spreadsheets/d/SPREADSHEET_ID/edit#gid=0
//
// test run script: https://script.google.com/macros/s/GAS_ID/exec?temperature=20&humidity=48
//-----------------------------------------------
// Author: Trieu Le
// Email: lethanhtrieuk36@gmail.com
// Publish date: 07-Oct-2015
// Description: This code for demonstration send data from ESP8266 into Google Spreadsheet
// GET request syntax:
// https://script.google.com/macros/s/<gscript id>/exec?header_here=data_here
// Modified by Moz for Youtube channel logMaker360 for this video: https://youtu.be/fS0GeaOkNRw 24-02-2018
**/

//-----------------------------------------------
/**
* Function doGet: Parse received data from GET request, 
  get and store data which is corresponding with header row in Google Spreadsheet
*/
function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters
  var result = 'Ok'; // assume success
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = ''; 		// Spreadsheet ID (FILL IN YOUR SPREADSHEET_ID HERE!)
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();		// get Active sheet
    var newRow = sheet.getLastRow() + 1;						
    var rowData = [];
    date = new Date();
    rowData[0] = date; 											// Timestamp in column A
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'temperature': //Parameter
          rowData[1] = value; //Value in column B
          result = 'Written on column B';
          break;
        case 'humidity': //Parameter
          rowData[2] = value; //Value in column C
          result += ' ,Written on column C';
          break;  
        default:
          result = "unsupported parameter";
      }
    }
    rowData[3] = date.toUTCString();
    rowData[4] = date.getTime(); // milliseconds since Jan 1, 1970 UTC
    Logger.log(JSON.stringify(rowData));
    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  // Return result of operation
  return ContentService.createTextOutput(result);
}
/**
* Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
/**
//-----------------------------------------------
// End of file
//-----------------------------------------------
*/
