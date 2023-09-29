#!/bin/bash

NODE_PATH=$(npm root --quiet -g) \
node --no-deprecation extract_map.js
