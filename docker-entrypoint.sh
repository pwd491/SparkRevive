#!/bin/sh
set -e

cd "$PLUGINROOT"
source ./make.sh $PLUGIN_TARGET
cd "$PLUGINAPP/$PLUGIN_TARGET/release/"
chmod -R +x ./plugin/var/bin/*
tar -cvf /app/output/$PLUGIN_TARGET.tar plugin