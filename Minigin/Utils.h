#pragma once
enum class ComponentType
{
	TextComponent, TextureComponent, FPSComponent, SubjectComponent, HealthComponent, PointComponent, SpriteSheetComponent, AiComponent, QBertComponent, GameManagerComponent, TileComponent, SpinningDisksComponent, CoilyComponent, BeginScreenComponent
};

enum class Event
{
	Kill, ColorChange, KillByFlyingDisc, RemainingDisc, CatchingSlickSam
};