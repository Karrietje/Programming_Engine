#pragma once
enum class ComponentType
{
	TextComponent, TextureComponent, FPSComponent, SubjectComponent, HealthComponent, PointComponent
};

enum class Event
{
	Kill, ColorChange, KillByFlyingDisc, RemainingDisc, CatchingSlick, CatchingSam
};