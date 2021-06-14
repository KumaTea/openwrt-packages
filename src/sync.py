import requests


packages = {
    'fish': {
        'cat': 'utils',
        'url': 'https://github.com/openwrt/packages/raw/master/utils/fish/Makefile'
    },
    'iperf3': {
        'cat': 'net',
        'url': 'https://github.com/openwrt/packages/raw/master/net/iperf3/Makefile'
    },
}


if __name__ == '__main__':
    for package in packages:
        pkg_dir = ['..', packages[package]['cat'], package, 'Makefile']
        pkg_path = '/'.join(pkg_dir)
        with open(pkg_path, 'wb') as f:
            print(f'Download pkg {package} to {pkg_path}')
            f.write(requests.get(packages[package]['url']).content)
