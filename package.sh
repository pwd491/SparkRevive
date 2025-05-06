

CURRENT_PATH=$PWD
PLUGIN_RELEASE_ROOT=./release/plugin
PLUGIN_RELEASE_FOLDER=$PLUGIN_RELEASE_ROOT/var
PLUGIN_RELEASE_TAR=plugin_temp.tgz
PLUGIN_INFOFILE=$PLUGIN_RELEASE_FOLDER/script/$PLUGIN_TARGET.sh
MD5CK=md5sum
SLASH=_

export LANG=zh_CH.gb2312
plugin_size=`du -cb $PLUGIN_RELEASE_FOLDER|grep 'total'|awk '{print $1}'`
plugin_name=`cat $PLUGIN_INFOFILE|grep -w "PLUGIN_NAME"|awk -F = '{print $2}'`
plugin_id=`cat $PLUGIN_INFOFILE|grep -w "PLUGIN_ID"|awk -F = '{print $2}'`
plugin_ver=`cat $PLUGIN_INFOFILE|grep -w "PLUGIN_VER"|awk -F = '{print $2}'`

rm -rf $PLUGIN_RELEASE_TAR
cd $PLUGIN_RELEASE_ROOT
tar -czf $PLUGIN_RELEASE_TAR var

plugin_cksum=`$MD5CK $PLUGIN_RELEASE_TAR|awk '{print $1}'`

echo $plugin_size
echo $plugin_name
echo $plugin_id
echo $plugin_ver
echo $plugin_cksum

rm -rf ../$plugin_id*.tgz
mv $PLUGIN_RELEASE_TAR ../$plugin_id$SLASH$plugin_name$SLASH$plugin_ver$SLASH$plugin_size$SLASH$plugin_cksum.tgz
cd $CURRENT_PATH