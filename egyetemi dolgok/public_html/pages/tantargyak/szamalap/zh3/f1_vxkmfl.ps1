if ( $args.Length -eq 1 )
{
   	Write-Host (Get-ChildItem $args  -Directory | Measure-Object | %{$_.Count}) K�nyt�r
    Write-Host (Get-ChildItem $args  -File | Measure-Object | %{$_.Count}) F�jl
}
ElseIf ( $args.Length -eq 0 )
{
Write-Host " Adja meg a mappa el�r�si �tvonal�t."
$a = Read-Host
   	Write-Host (Get-ChildItem $a  -Directory | Measure-Object | %{$_.Count}) K�nyt�r
    Write-Host (Get-ChildItem $a  -File | Measure-Object | %{$_.Count}) F�jl
}
ElseIf ( $args.Length -gt 1 )
{

Write-Host " T�l sok param�ter"
}