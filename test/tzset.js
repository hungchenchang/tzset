var tzset = require('bindings')('tzset.node')

console.log('This should be 0:', tzset.tzset());
