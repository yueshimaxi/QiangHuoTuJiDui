#include "XuCheckBox.h"


UXuCheckBox::UXuCheckBox()
{
	OnCheckStateChanged.AddDynamic(this, &UXuCheckBox::OnCheckBoxStateChanged);
}

void UXuCheckBox::OnCheckBoxStateChanged(bool b_is_checked)
{
	XuOnCheckStateChanged.ExecuteIfBound(b_is_checked);
}
