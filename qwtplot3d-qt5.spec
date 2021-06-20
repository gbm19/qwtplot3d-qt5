%undefine __cmake_in_source_build

%global commit 45df8fbad445dbb71bfc17672ea669e76688946c
%global gittag %{commit}
%global shortcommit %(c=%{commit}; echo ${c:0:7})
%global commitdate 20200509

Name:           qwtplot3d-qt5
Version:        0.3.1a
Release:        13.%{commitdate}git%{shortcommit}%{?dist}
Summary:        Extended version of the original QwtPlot3D library
# zlib/libpng is main license
# LGPLv2+ or GL2PS is the license for 'gl2ps/' files
License:        zlib and (LGPLv2+ or GL2PS)
URL:            https://github.com/copasi/copasi-dependencies/tree/master/src/qwtplot3d-qt4
Source0:        https://gitlab.com/anto.trande/qwtplot3d-qt4/-/archive/%{commit}/qwtplot3d-qt4-%{commit}.tar.gz
Patch0:         qwtplot3d-qt5-build.patch

Requires:       pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(glu)
BuildRequires:  pkgconfig(xmu)
Buildrequires:  qt5-rpm-macros, qt5-qtbase-devel
#BuildRequires:  gl2ps-devel
BuildRequires:  gcc-c++, zlib-devel

Provides: bundled(gl2ps) = 1.3.2

%description
QwtPlot3D is not a program, but a feature-rich Qt/OpenGL-based C++
programming library, providing essentially a bunch of 3D-widgets for
programmers.

%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    devel
The %{name}-devel package contains qt5 libraries and header files for
developing applications that use %{name}.

%prep
%autosetup -n qwtplot3d-qt4-%{commit} -p0

%build
%cmake -Wno-dev \
 -DSELECT_QT=Qt5 \
 -DQT_QMAKE_EXECUTABLE:FILEPATH=%{_bindir}/qmake-qt5 \
 -DQWT_VERSION_STRING:STRING=6.1.3 \
 -DQWT_LIBRARY:FILEPATH=%{_qt5_libdir}/libqwt-qt5.so \
 -DQWT_INCLUDE_DIR:PATH=%{_qt5_headerdir}/qwt \
 -DCMAKE_BUILD_TYPE:STRING=Release \
 -DCMAKE_VERBOSE_MAKEFILE:BOOL=TRUE -DCMAKE_COLOR_MAKEFILE:BOOL=ON \
 -DCMAKE_SHARED_LINKER_FLAGS_RELEASE:STRING="%{__global_ldflags} -lGLU" \
 -DWITH_ZLIB:BOOL=ON \
 -DCMAKE_INSTALL_LIBDIR:PATH=%{_qt5_libdir} -DCMAKE_INSTALL_INCLUDEDIR:PATH=%{_qt5_headerdir}/%{name}
%cmake_build

%install
%cmake_install

%ldconfig_scriptlets

%files
%license COPYING 3rdparty/gl2ps/COPYING.*
%{_qt5_libdir}/lib%{name}.so.*

%files devel
%{_qt5_headerdir}/%{name}/
%{_qt5_libdir}/lib%{name}.so

%changelog
* Wed Jan 27 2021 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-13.20200509git45df8fb
- Rebuilt for https://fedoraproject.org/wiki/Fedora_34_Mass_Rebuild

* Sat Aug 01 2020 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-12.20200509git45df8fb
- Second attempt - Rebuilt for
  https://fedoraproject.org/wiki/Fedora_33_Mass_Rebuild

* Wed Jul 29 2020 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-11.20200509git45df8fb
- Rebuilt for https://fedoraproject.org/wiki/Fedora_33_Mass_Rebuild

* Sat May 09 2020 Antonio Trande <sagitter@fedoraproject.org> - 0.3.1a-10.20200509git45df8fb
- Build commit #45df8fb

* Sat May 09 2020 Antonio Trande <sagitter@fedoraproject.org> - 0.3.1a-9.20200509git62eca37
- Move code to GitLab repository
- Rebuild new commit

* Thu Jan 30 2020 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-8.20170803git34d8141
- Rebuilt for https://fedoraproject.org/wiki/Fedora_32_Mass_Rebuild

* Fri Jul 26 2019 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-7.20170803git34d8141
- Rebuilt for https://fedoraproject.org/wiki/Fedora_31_Mass_Rebuild

* Sat Feb 02 2019 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-6.20170803git34d8141
- Rebuilt for https://fedoraproject.org/wiki/Fedora_30_Mass_Rebuild

* Sat Jul 14 2018 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-5.20170803git34d8141
- Rebuilt for https://fedoraproject.org/wiki/Fedora_29_Mass_Rebuild

* Sat May 05 2018 Antonio Trande <sagitter@fedoraproject.org> - 0.3.1a-4.20170803git34d8141
- Build new commit from COPASI repository
- Use CMake method

* Sat Feb 17 2018 Antonio Trande <sagitter@fedoraproject.org> - 0.3.1a-3.20170630gite30f5df
- Use %%ldconfig_scriptlets

* Fri Feb 09 2018 Fedora Release Engineering <releng@fedoraproject.org> - 0.3.1a-2.20170630gite30f5df
- Rebuilt for https://fedoraproject.org/wiki/Fedora_28_Mass_Rebuild

* Sun Nov 12 2017 Antonio Trande <sagitter@fedoraproject.org> - 0.3.1a-1.20170630gite30f5df
- Update to 0.3.1 (pre-release)
- Build QT5 library
