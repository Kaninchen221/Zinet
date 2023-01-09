from pg.safe_dict import SafeDict

class CMakeListsGenerator:
    def generate_cmakelists(self, templatePath, dictionary):
        template = open(templatePath).read()
        cmakelists = template.format_map(dictionary)
        return cmakelists

    def prepare_arguments(self):
        return SafeDict()
