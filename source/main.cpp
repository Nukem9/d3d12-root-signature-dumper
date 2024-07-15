#include <fstream>
#include <memory>
#include "D3DRootSignature.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: RootSigDumper.exe <root_signature.bin>\n");
		printf("(Input binaries are created with \"dxc.exe -dumpbin <shader.bin> -Qstrip_rootsignature -Fo <root_signature.bin>\")\n");
		printf("\n");
		return 1;
	}

	if (std::ifstream f(argv[1], std::ios::binary | std::ios::ate); f.good())
	{
		auto fileSize = static_cast<uint64_t>(f.tellg());
		auto fileData = std::make_unique<uint8_t[]>(fileSize);

		f.seekg(0, std::ios::beg);
		f.read(reinterpret_cast<char *>(fileData.get()), fileSize);

		ID3D12VersionedRootSignatureDeserializer *deserializer = nullptr;
		if (FAILED(D3D12CreateVersionedRootSignatureDeserializer(fileData.get(), fileSize, IID_PPV_ARGS(&deserializer))))
		{
			printf("Failed to create root signature deserializer\n");
			return 1;
		}

		const D3D12_VERSIONED_ROOT_SIGNATURE_DESC *desc = nullptr;
		if (FAILED(deserializer->GetRootSignatureDescAtVersion(D3D_ROOT_SIGNATURE_VERSION_1_1, &desc)))
		{
			printf("Failed to convert root signature 1.1 description\n");
			return 1;
		}

		const auto asText = D3DRootSignature::RootSignatureToString(desc->Desc_1_1);
		printf("%s\n", asText.c_str());

		return 0;
	}

	printf("File not found or unreadable: %s\n", argv[1]);
	return 1;
}
