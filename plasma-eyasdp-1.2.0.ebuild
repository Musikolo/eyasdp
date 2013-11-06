# Gentoo Linux ebuild installation script
# Contributor: Kroz
# Distributed under the terms of the GNU General Public License v2

EAPI=5

KDE_MINIMAL="4.7.0"
QT_MINIMAL="4.7.0"

inherit cmake-utils kde4-base

DESCRIPTION="KDE4 plasmoid. eYaSDP allows to set a number of system buttons in your panel or desktop for comfortable and quick access."
HOMEPAGE="http://kde-look.org/content/show.php/eYaSDP?content=146530"
SRC_URI="http://kde-look.org/CONTENT/content-files/146530-eyasdp-1.2.0.tar.bz2"

S="${WORKDIR}/${P#plasma-}"

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE=""

DEPEND="$(add_kdebase_dep plasma-workspace)"
RDEPEND="${DEPEND}"