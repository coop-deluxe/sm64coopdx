{
    description = "dev environment for n64 decomp";
    inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";
    outputs = { self, ... } @ inputs:
    let
        inherit (inputs.nixpkgs) lib;
        supportedSystems = [
            "x86_64-linux"
            "aarch64-linux"
            "aarch64-darwin"
        ];
        forEachSupportedSystem =
        f: lib.genAttrs supportedSystems (
            system: f {
                inherit system;
                pkgs = import inputs.nixpkgs { inherit system; };
            }
        );
        version = "3.14";
    in {
        devShells = forEachSupportedSystem (
            { pkgs, system }:
            let
                concatMajorMinor = v: lib.pipe v [ lib.versions.splitVersion (lib.sublist 0 2) lib.concatStrings ];
                python = pkgs."python${concatMajorMinor version}";
            in {
                default = pkgs.mkShell.override {
                    # override stdenv
                } {
                    venvDir = ".venv";
                    packages = (with pkgs; [
                        pkg-config
                        SDL2
                        zlib
                        glew
                        curlFull
                        blender
                        # sm64tool
                        capstone
                        stb
                        libyaml
                    ]) ++ (with python.pkgs; [
                        venvShellHook
                        pip
                    ]);
                };
            }
        );
    };
}
