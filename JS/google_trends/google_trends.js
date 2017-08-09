'use strict';

var googleTrends = require('./google-trends-api.min.js');
var util = require('util');

googleTrends.interestOverTime({keyword: 'Valentines Day'})
.then((res) => {
  console.log('this is res', res);
})
.catch((err) => {
  console.log('got the error', err);
  console.log('error message', err.message);
  console.log('request body',  err.requestBody);
});

googleTrends.interestOverTime({keyword: 'Valentines Day', startTime: new Date(Date.now() - (4 * 60 * 60 * 1000))}, function(err, results) {
  if (err) console.log('oh no error!', err);
  else console.log(results);
});