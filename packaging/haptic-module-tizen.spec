#sbs-git:slp/pkgs/d/devman devman 0.1.6 5bf2e95e0bb15c43ff928f7375e1978b0accb0f8
Name:       haptic-module-tizen
Summary:    Haptic Module library
Version:    0.1.0
Release:    1
Group:      System/Libraries
License:    LGPL 2.1
Source0:    %{name}-%{version}.tar.gz
BuildRequires: cmake
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(vconf)
BuildRequires: pkgconfig(haptic-plugin)
BuildRequires: pkgconfig(devman)

Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description

%prep
%setup -q

%build
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_libdir}/haptic/libhaptic-module.so
%{_bindir}/test1

%changelog
* Mon Nov 19 2012 - Jiyoung Yun <jy910.yun@samsung.com>
- fix the problem not working on emulator
- Tag : haptic-module-tizen_0.1.0-1

* Fri Nov 02 2012 - Jae-young Hwang <j-zero.hwang@samsung.com>
- Implement haptic-module-tizen
- Tag : haptic-module-tizen_0.1.0-0
