{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
  };

  outputs = { self, nixpkgs, ... }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell.override { stdenv = pkgs.gcc13Stdenv; } {
      nativeBuildInputs = with pkgs; [
        cmake
        conan
        ninja
        mold
        ccache
      ];
      shellHook = ''
        export IN_NIX_SHELL=1
        export LD_LIBRARY_PATH="${pkgs.gcc13Stdenv.cc.cc.lib}/lib:$LD_LIBRARY_PATH"
      '';
    };
  };
}
