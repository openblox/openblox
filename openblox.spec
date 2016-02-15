Name:           openblox
Version:        0.1.1
Release:        1%{?dist}
Summary:        Reference client implementation for the OpenBlox game engine.

License:        LGPLv3+
URL:            https://git.openblox.org/openblox.git/
Source0:        https://openblox.org/~johnmh/openblox/openblox-master.tar.gz

BuildRequires:  libopenblox-devel

#Since these aren't automatically pulled in because of libopenblox-devel..
BuildRequires:  qt5-qtbase-devel SDL2-devel libcurl-devel openal-soft-devel freealut-devel ogre-devel lua-devel libraknet-devel
Requires:       libopenblox

%description
The reference client implementation for the OpenBlox game engine, which
implements a simple and easy to learn Lua based API, similar to that
of the proprietary ROBLOX game platform.

%prep
%setup -q -n openblox-master

%build
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
%make_install
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'

%files
%{_bindir}/openblox
%{_mandir}/man1/*

%changelog
* Sat Feb 13 2016 - 0.1.1
- Initial packaging of openblox.
