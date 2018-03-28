Name: libsailfishapp
Version: 1
Release: 1
Summary: Sailfish Application Library
Group: Development/Libraries
License: LGPLv2.1
URL: https://github.com/sailfishos/libsailfishapp
Source: %{name}-%{version}.tar.bz2
BuildRequires: pkgconfig(Qt5Gui)
BuildRequires: pkgconfig(Qt5Quick)
BuildRequires: pkgconfig(Qt5Qml)
BuildRequires: pkgconfig(qdeclarative5-boostable)
BuildRequires: pkgconfig(mlite5)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
This library should be used by Sailfish applications to create a QML view.
libsailfishapp will take care of using the booster if possible, and will
also make sure that applications built with the Sailfish SDK are future-
proof, by putting all special cases inside libsailfishapp, where it can be
updated by the vendor.

%package devel
Summary: Development library for Sailfish apps
Requires: %{name} = %{version}
Requires: pkgconfig(qdeclarative5-boostable)

%description devel
This package contains the development library for %{name}.

%package launcher
Summary: QML application launcher for Sailfish apps

%description launcher
This package contains "sailfish-qml", the pure QML Sailfish app launcher.

%package doc
Summary: Documentation for %{name}.
BuildRequires: mer-qdoc-template

%description doc
This package contains the documentation for %{name}.

%prep
%setup -q

%build
%qmake5 -r VERSION=%{version}
make

%install
make install INSTALL_ROOT=%{buildroot}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/%{name}.so.*

%files launcher
%defattr(-,root,root,-)
%{_bindir}/sailfish-qml

%files devel
%defattr(-,root,root,-)
%{_libdir}/%{name}.so
%{_libdir}/pkgconfig/sailfishapp.pc
%{_datadir}/qt5/mkspecs/features/sailfishapp.prf
%{_datadir}/qt5/mkspecs/features/sailfishapp_qml.prf
%{_datadir}/qt5/mkspecs/features/sailfishapp_i18n.prf
%{_includedir}/sailfishapp/sailfishapp.h

%files doc
%defattr(-,root,root,-)
%{_defaultdocdir}
