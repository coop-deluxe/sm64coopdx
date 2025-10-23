import sys

VECX_TO_VECY = """
/* |description|
Converts a {{size}}D {{desc}} vector `a` into a {{size}}D {{desc_2}} vector and stores the result in `dest`
|descriptionEnd| */
INLINE OPTIMIZE_O3 Vec{{size}}{{suffix_2}}p vec{{size}}{{suffix}}_to_vec{{size}}{{suffix_2}}(OUT Vec{{size}}{{suffix_2}} dest, Vec{{size}}{{suffix}} a) {
    {{body}}
    return dest;
}
"""

ROUNDING_FORMULA = " + ((a[{i}] > 0) ? 0.5f : -0.5f)"

def vec_write_conversion_functions(generated: str, curr_template: dict, templates: list, size: int) -> str:
    for template in templates:
        if template["suffix"] == curr_template["suffix"]:
            continue

        body = "\n    ".join([
            "dest[{i}] = a[{i}]{rounding};".format(
                i=i,
                rounding=ROUNDING_FORMULA.format(i=i) if curr_template["rounding"] else ""
            ) for i in range(size)
        ])

        generated += VECX_TO_VECY \
            .replace("{{size}}", str(size)) \
            .replace("{{desc}}", curr_template["desc"]) \
            .replace("{{suffix}}", curr_template["suffix"]) \
            .replace("{{desc_2}}", template["desc"]) \
            .replace("{{suffix_2}}", template["suffix"]) \
            .replace("{{body}}", body)

    return generated


TEMPLATES = {
    "src/engine/math_util_vec2.tmpl": {
        "size": 2,
        "templates": [
            {
                "desc": "floating-point",
                "type": "f32",
                "suffix": "f",
                "rounding": True
            },
            {
                "desc": "integer",
                "type": "s32",
                "suffix": "i",
                "rounding": False
            },
            {
                "desc": "short integer",
                "type": "s16",
                "suffix": "s",
                "rounding": False
            }
        ],
        "post-template": {
            "function": vec_write_conversion_functions,
            "args": {
                "size": 2
            }
        }
    },
    "src/engine/math_util_vec3.tmpl": {
        "size": 3,
        "templates": [
            {
                "desc": "floating-point",
                "type": "f32",
                "suffix": "f",
                "rounding": True
            },
            {
                "desc": "integer",
                "type": "s32",
                "suffix": "i",
                "rounding": False
            },
            {
                "desc": "short integer",
                "type": "s16",
                "suffix": "s",
                "rounding": False
            }
        ],
        "post-template": {
            "function": vec_write_conversion_functions,
            "args": {
                "size": 3
            }
        }
    }
}


def main():
    verbose = len(sys.argv) > 1 and (sys.argv[1] == "-v" or sys.argv[1] == "--verbose")
    for template_file, x in TEMPLATES.items():
        with open(template_file) as f:
            tmpl = f.read()
        templates = x["templates"]
        post_template = x.get("post-template", None)

        if verbose:
            print("Generating the following files from template: %s" % (template_file))

        for template in templates:
            generated = (
                "/* THIS FILE IS AUTO-GENERATED */\n" +
                "/*   DO NOT EDIT IT MANUALLY   */\n\n" +
                tmpl
            )

            for template_field, template_replacement in template.items():
                generated = generated.replace("{{" + template_field + "}}", str(template_replacement))

            if post_template:
                generated = post_template["function"](generated, template, templates, **post_template["args"])

            generated_filename = template_file[:template_file.rfind(".")] + template["suffix"] + ".inl"
            with open(generated_filename, 'w', encoding='utf-8', newline='\n') as f:
                f.write(generated)

            if verbose:
                print(">>> %s" % (generated_filename))


if __name__ == "__main__":
    main()
