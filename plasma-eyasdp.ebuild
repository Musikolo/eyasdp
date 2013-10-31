EYASDP_VERSION="1.1.0"
EAPI=5

KDE_MINIMAL="4.7.0"
QT_MINIMAL="4.7.0"

inherit cmake-utils kde4-base

DESCRIPTION="KDE4 plasmoid. eYaSDP allows to set a number of system buttons in your panel or desktop for comfortable and quick access."
HOMEPAGE="http://kde-look.org/content/show.php/eYaSDP?content=146530"
SRC_URI="http://kde-look.org/CONTENT/content-files/146530-eyasdp-${EYASDP_VERSION}.tar.bz2"

S="${WORKDIR}/eyasdp-${EYASDP_VERSION}"

LICENSE="GPL"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE=""

DEPEND="
x11-libs/libX11
x11-libs/libXext
x11-libs/libXft
x11-libs/libXau
x11-libs/libXdmcp
x11-libs/libXpm
dev-libs/openssl
dev-util/automoc
dev-lang/perl
"
RDEPEND="${DEPEND}"