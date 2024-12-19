{
  description = "A simple C library for defer statement.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-parts.url = "github:hercules-ci/flake-parts";
  };

  outputs =
    { flake-parts, ... }@inputs:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" ];

      perSystem =
        { self', pkgs, ... }@pinputs:
        let
          stdenv' = pkgs.gcc14Stdenv;
        in
        {
          packages = import ./nix/packages.nix pinputs stdenv';
          devShells = import ./nix/devshells.nix pinputs stdenv';
        };
    };
}
