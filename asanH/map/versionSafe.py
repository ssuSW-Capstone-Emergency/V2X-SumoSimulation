# Veins에 default로 설치된 SUMO와의 버전이 맞지 않아 발생하는 참조 충돌 해결 위한 코드

import re
import xml.etree.ElementTree as ET

def remove_disallowed_words(xml_string, words_to_remove):
    pattern = r'disallow="([^"]*)"'
    
    def replace_disallow(match):
        disallow_content = match.group(1)
        filtered_content = ' '.join(word for word in disallow_content.split() if word not in words_to_remove)
        return f'disallow="{filtered_content}"'
    
    modified_xml = re.sub(pattern, replace_disallow, xml_string)
    return modified_xml

# 제거하고 싶은 단어들의 리스트(SUMO 1.11.0에서 지원하지 않는 참조)
words_to_remove = ["container", "cable_car", "subway", "aircraft", "wheelchair", "drone"]

# 입력 파일 읽기
input_file = "asanH.net.xml"
output_file = "asanH_1_11_0.net.xml"

try:
    # XML 파일 파싱
    tree = ET.parse(input_file)
    root = tree.getroot()

    # XML을 문자열로 변환
    xml_string = ET.tostring(root, encoding='unicode')

    # disallow 속성 수정
    modified_xml = remove_disallowed_words(xml_string, words_to_remove)

    # 수정된 XML 문자열을 ElementTree로 다시 파싱
    modified_root = ET.fromstring(modified_xml)

    # 수정된 XML 트리를 파일로 저장
    modified_tree = ET.ElementTree(modified_root)
    modified_tree.write(output_file, encoding="utf-8", xml_declaration=True)

    # print(f"수정된 파일이 {output_file}로 저장되었습니다.")

except FileNotFoundError:
    print(f"파일을 찾을 수 없습니다: {input_file}")
except ET.ParseError:
    print(f"XML 파싱 오류: {input_file}")
except Exception as e:
    print(f"오류 발생: {str(e)}")