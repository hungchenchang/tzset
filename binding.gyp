{
  "targets": [
    {
      "target_name": "tzset",
      "sources": [ "tzset.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
