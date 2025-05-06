#!/bin/sh
set -e

cd "$PLUGINROOT"
source ./make.sh camconfig
cd "$PLUGINAPP/camconfig/release/"
tar -czvf /app/output/camconfig_0.1.tar.gz plugin