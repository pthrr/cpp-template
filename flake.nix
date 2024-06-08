{
  description = "cpp-template";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, }: utils.lib.eachDefaultSystem (system: let
    pkgs = import nixpkgs { inherit system; };
  in {
    devShells.default = pkgs.mkShell.override { stdenv = pkgs.gcc13Stdenv; } {
      packages = with pkgs; [
        cmake
        conan
        ninja
        mold
        ccache
        python3
      ];

      shellHook = ''
        export IN_NIX_SHELL=1
        export QT_PLUGIN_PATH="$QT_PLUGIN_PATH:${pkgs.qt6.qtwayland}/lib/qt-6/plugins"
        export QT_QPA_PLATFORM="wayland;xcb"
      '';
    };
  });
}
