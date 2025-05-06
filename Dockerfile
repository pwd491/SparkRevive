FROM jalle19/centos7-stlinux24


RUN export PATH="/opt/STM/STLinux-2.4/devkit/sh4/bin:$PATH"

RUN ln -s /opt/STM/STLinux-2.4/devkit/sh4/bin/sh4-linux-gcc /usr/local/bin/gcc
RUN ln -s /opt/STM/STLinux-2.4/devkit/sh4/bin/sh4-linux-g++ /usr/local/bin/g++

RUN rm -f /etc/yum.repos.d/*.repo

RUN cat > /etc/yum.repos.d/CentOS.repo <<'EOF'
[base]
name=CentOS-7.9.2009 - Base
baseurl=http://vault.centos.org/7.9.2009/os/$basearch/
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
enabled=1
metadata_expire=never

[updates]
name=CentOS-7.9.2009 - Updates
baseurl=http://vault.centos.org/7.9.2009/updates/$basearch/
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
enabled=1
metadata_expire=never

[extras]
name=CentOS-7.9.2009 - Extras
baseurl=http://vault.centos.org/7.9.2009/extras/$basearch/
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
enabled=1
metadata_expire=never

[centosplus]
name=CentOS-7.9.2009 - CentOSPlus
baseurl=http://vault.centos.org/7.9.2009/centosplus/$basearch/
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
enabled=0
metadata_expire=never

[fasttrack]
name=CentOS-7.9.2009 - Contrib
baseurl=http://vault.centos.org/7.9.2009/fasttrack/$basearch/
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
enabled=0
metadata_expire=never
EOF
RUN cat > /etc/yum.repos.d/epel.repo <<'EOF'
[epel]
name=Extra Packages for Enterprise Linux 7 - $basearch
baseurl=https://archives.fedoraproject.org/pub/archive/epel/7/$basearch
enabled=1
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7
metadata_expire=never
[epel-debuginfo]
name=Extra Packages for Enterprise Linux 7 - $basearch - Debug
baseurl=https://archives.fedoraproject.org/pub/archive/epel/7/$basearch/debug
enabled=0
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7
gpgcheck=1
metadata_expire=never
[epel-source]
name=Extra Packages for Enterprise Linux 7 - $basearch - Source
baseurl=https://archives.fedoraproject.org/pub/archive/epel/7/SRPMS
enabled=0
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7
gpgcheck=1
metadata_expire=never
EOF

RUN yum clean all && yum makecache
RUN yum --assumeyes update
RUN find /etc/yum.repos.d/ -type f -not \( -name "CentOS.repo" -o -name "epel.repo" \) -delete
RUN yum clean all && yum makecache
RUN yum --assumeyes --nogpgcheck install net-tools bind-utils epel-release git ccache

WORKDIR /root/spark
COPY . .