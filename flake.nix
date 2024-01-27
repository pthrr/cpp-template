{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
  };

  outputs = { self , nixpkgs ,... }: let
    system = "x86_64-linux";
  in {
    devShells."${system}".default = let
      pkgs = import nixpkgs {
        inherit system;
      };
    in pkgs.mkShell {
      packages = with pkgs; [
        zig
        cmake
        conan
        ninja
        mold
        ccache
      ];
      shellHook = ''
        export CC="zigcc"
        export CXX="zigcxx"
        export LD="zigcc"
        export AR="zigar"
        export OBJCOPY="zigobjcopy"
      '';
    };
  };
}
